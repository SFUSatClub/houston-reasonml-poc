type root;

type commandArgument = {
  .
  "id": string,
  "name": string,
  "value": string,
};

type command = {
  .
  "id": string,
  "name": string,
  "timeout": int,
  "wait": int,
  "arguments": list(commandArgument),
};

type commandSequence = {
  .
  "id": string,
  "name": string,
  "description": string,
  "commands": list(command),
};

type commandArgumentInput = {
  .
  "name": string,
  "value": string,
};

type commandInput = {
  .
  "name": string,
  "timeout": int,
  "wait": int,
  "arguments": list(commandArgumentInput),
};

type commandSequenceInput = {
  .
  "name": string,
  "description": string,
  "commands": list(commandInput),
};

type createCommandSequenceArg = {. "sequence": commandSequenceInput};

[@bs.val] [@bs.module "./helpers"]
external readJsonFile : string => Js.Promise.t(commandSequence) = "";

[@bs.val] [@bs.module "./helpers"]
external writeJsonFile : (string, commandSequence) => Js.Promise.t(string) =
  "";

[@bs.val] [@bs.module "./helpers"]
external injectIdToObjTree : commandSequenceInput => commandSequence = "";

let createCommandSequence = (_root, args) => {
  let commandSequenceInput = args##sequence;
  let commandSequence = injectIdToObjTree(commandSequenceInput);
  let path = "src/command_sequence/" ++ commandSequence##id ++ ".json";

  writeJsonFile(path, commandSequence)
  |> Js.Promise.then_(path => readJsonFile(path));
};

type mutation = {
  .
  "createCommandSequence":
    (root, createCommandSequenceArg) => Js.Promise.t(commandSequence),
};

let resolvers: mutation = {"createCommandSequence": createCommandSequence};