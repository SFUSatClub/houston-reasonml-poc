type root;

/* Create wrappers for the helper functions so we can call them within the ReasonML code */

[@bs.val] [@bs.module "./helpers"]
external readCommandSequence : string => Js.Promise.t(Schema.commandSequence) =
  "readJsonFile";

/* Mirrors the Query type in the GraphQL schema */

type query = {
  .
  "findCommandSequence":
    (root, {. "id": string}) => Js.Promise.t(Schema.commandSequence),
};

/*
   Actual implementation of the root resolvers
   Note that the resolvers take "store" as a dependency. We inject a store value in the "Resolvers.re" file.
   Since non of the resolvers use the store value, we are ignoring it for now.
 */

let resolvers: Store.t(State.state, Action.action) => query =
  _store => {
    "findCommandSequence": (_root, args) => {
      let path = "src/command_sequence/" ++ args##id ++ ".json";
      readCommandSequence(path);
    },
  };