open SchemaInputTypes;
open SchemaTypes;

type root;

type query = {
  .
  "findCommandSequence":
    (root, {. "id": string}) => Js.Promise.t(commandSequence),
};

type mutation = {
  .
  "createCommandSequence":
    (root, {. "sequence": commandSequenceInput}) =>
    Js.Promise.t(commandSequence),
  "uplinkCommandSequence": (root, {. "id": string}) => Js.Promise.t(bool),
};

type subscription = {. "state": {. "subscribe": unit => Pubsub.stream}};