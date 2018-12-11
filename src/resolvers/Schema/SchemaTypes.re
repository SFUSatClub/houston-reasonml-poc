type commandArgument = {
  .
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