type root;

/* Create wrappers for the helper functions so we can call them within the ReasonML code */

[@bs.val] [@bs.module "./helpers"]
external readJsonFile : string => Js.Promise.t(Schema.commandSequence) = "";

/* Mirrors the Query type in the GraphQL schema */

type query = {
  .
  "info": unit => string,
  "commandSequence":
    (root, {. "id": string}) => Js.Promise.t(Schema.commandSequence),
};

/*
   Actual implementation of the root resolvers
   Note that the resolvers take "store" as a dependency. We inject a store value in the "Resolvers.re" file.
   Since non of the resolvers use the store value, we are ignoring it for now.
 */

let resolvers: Store.t(State.state, Action.action) => query =
  _store => {
    "info": () => "Houston ReasonML PoC: Houston is SFU Satellite design team's ground control station",
    "commandSequence": (_root, args) => {
      let path = "src/command_sequence/" ++ args##id ++ ".json";
      readJsonFile(path);
    },
  };