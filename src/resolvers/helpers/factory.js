module.exports = ({ fs, hash }) => {
  const readJsonFile = path => {
    return new Promise((resolve, reject) => {
      fs.readFile(path, (error, data) => {
        if (error) reject(error);
        else resolve(JSON.parse(data));
      });
    });
  };

  const writeJsonFile = (path, sequence, indent = 2) => {
    return new Promise((resolve, reject) => {
      fs.writeFile(path, JSON.stringify(sequence, null, indent), error => {
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

  const injectSequenceAndCommandIds = commandSequence => ({
    ...commandSequence,
    id: hash(commandSequence),
    commands: commandSequence.commands.map((c, i) => ({ ...c, id: `${i}` }))
  });

  return {
    readJsonFile,
    writeJsonFile,
    injectSequenceAndCommandIds
  };
};
