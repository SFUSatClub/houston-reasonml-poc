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