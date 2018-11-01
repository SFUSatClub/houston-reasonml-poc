type root;

[@bs.val] [@bs.module "./helpers"]
external readJsonFile : string => Js.Promise.t(Schema.commandSequence) = "";

type query = {
  .
  "info": unit => string,
  "commandSequence":
    (root, {. "id": string}) => Js.Promise.t(Schema.commandSequence),
};

let resolvers: Store.t(State.state, Action.action) => query =
  _store => {
    "info": () => "Houston ReasonML PoC: Houston is SFU Satellite design team's ground control station",
    "commandSequence": (_root, args) => {
      let path = "src/command_sequence/" ++ args##id ++ ".json";
      readJsonFile(path);
    },
  };