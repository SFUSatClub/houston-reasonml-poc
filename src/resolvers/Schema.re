/* Mirrors the type definitions in the GraphQL Schema. */

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

type commandArgument = commandArgumentInput;

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

type state = {
  .
  "state": {
    .
    "uplink": {
      .
      "sequenceId": Js.Nullable.t(string),
      "pending": array(string),
      "unresolved": array(string),
      "successful": array(string),
      "failed": array(string),
      "inProgress": bool,
    },
  },
};