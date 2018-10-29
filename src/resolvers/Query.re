type root;

type commandSequenceArg = {. "id": string};

[@bs.val] [@bs.module "./helpers"]
external readJsonFile : string => Js.Promise.t(Schema.commandSequence) = "";

type query = {
  .
  "info": unit => string,
  "commandSequence":
    (root, commandSequenceArg) => Js.Promise.t(Schema.commandSequence),
};

let resolvers: query = {
  "info": () => "Houston ReasonML PoC: Houston is SFU Satellite design team's ground control station",
  "commandSequence": (_root, args) => {
    let path = "src/command_sequence/" ++ args##id ++ ".json";
    readJsonFile(path);
  },
};