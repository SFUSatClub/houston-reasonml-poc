open Schema;

/* We don't access the root for the root resolvers so i'm defining an abstract type for it. */
type root;

/* Create wrappers for the helper functions so we can call them within the ReasonML code */

[@bs.val] [@bs.module "./helpers"]
external readJsonFile : string => Js.Promise.t(commandSequence) = "";

[@bs.val] [@bs.module "./helpers"]
external writeJsonFile : (string, commandSequence) => Js.Promise.t(string) =
  "";

[@bs.val] [@bs.module "./helpers"]
external injectIdToObjTree : commandSequenceInput => commandSequence = "";

/* Mirrors the Mutation type in the GraphQL schema */

type mutation = {
  .
  "createCommandSequence":
    (root, {. "sequence": commandSequenceInput}) =>
    Js.Promise.t(commandSequence),
  "executeCommandSequence": (root, {. "id": string}) => Js.Promise.t(bool),
};

/*
   Actual implementation of the root resolvers.
   Note that the resolvers take "store" as a dependency. We inject a store value in the "Resolvers.re" file.
 */

let createCommandSequence = (_root, args) => {
  let commandSequenceInput = args##sequence;
  let commandSequence = injectIdToObjTree(commandSequenceInput);
  let path = "src/command_sequence/" ++ commandSequence##id ++ ".json";

  writeJsonFile(path, commandSequence)
  |> Js.Promise.then_(path => readJsonFile(path));
};

let executeCommandSequence = store => {
  let uplink = Uplink.uplink(store);

  (_root, args) => {
    let path = "src/command_sequence/" ++ args##id ++ ".json";
    readJsonFile(path)
    |> Js.Promise.then_(sequence => {
         let (start, _stop) = uplink(sequence);
         start();
         Js.Promise.resolve(true);
       });
  };
};

let resolvers: Store.t(State.state, Action.action) => mutation =
  store => {
    "createCommandSequence": createCommandSequence,
    "executeCommandSequence": executeCommandSequence(store),
  };