module.exports = ({ fs, hash }) => {
  const readJsonFile = path => {
    return new Promise((resolve, reject) => {
      fs.readFile(path, (error, data) => {
        if (error) reject(error);
        else resolve(JSON.parse(data));
      });
    });
  };

  const writeJsonFile = (path, sequence) => {
    return new Promise((resolve, reject) => {
      fs.writeFile(path, JSON.stringify(sequence, null, 2), error => {
        if (error) reject(error);
        else resolve(path);
      });
    });
  };

  const injectIdToObjTree = root => {
    const res = { ...root, id: hash(root) };

    Object.entries(res).forEach(([key, value]) => {
      if (Array.isArray(value)) {
        res[key] = value.map(v => injectIdToObjTree(v));
      }
    });

    return res;
  };

  return {
    readJsonFile,
    writeJsonFile,
    injectIdToObjTree
  };
};
