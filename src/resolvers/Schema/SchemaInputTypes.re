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