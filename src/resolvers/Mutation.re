open Schema;

/* Create wrappers for the helper functions so we can call them within the ReasonML code */

[@bs.val] [@bs.module "./helpers"]
external readCommandSequence : string => Js.Promise.t(commandSequence) =
  "readJsonFile";

[@bs.val] [@bs.module "./helpers"]
external writeCommandSequence :
  (string, commandSequence) => Js.Promise.t(string) =
  "writeJsonFile";

[@bs.val] [@bs.module "./helpers"]
external injectSequenceAndCommandIds : commandSequenceInput => commandSequence =
  "";

/*
   Actual implementation of the root resolvers.
   Note that the resolvers take "store" as a dependency. We inject a store value in the "Resolvers.re" file.
 */

let createCommandSequence = (_root, args) => {
  let commandSequenceInput = args##sequence;
  let commandSequence = injectSequenceAndCommandIds(commandSequenceInput);
  let path = "src/command_sequence/" ++ commandSequence##id ++ ".json";

  writeCommandSequence(path, commandSequence)
  |> Js.Promise.then_(path => readCommandSequence(path));
};

let uplinkCommandSequence = dep => {
  let uplink = Uplink.create(dep);

  (_root, args) => {
    let path = "src/command_sequence/" ++ args##id ++ ".json";
    readCommandSequence(path)
    |> Js.Promise.then_(sequence => {
         Uplink.start(uplink, sequence);
         Js.Promise.resolve(true);
       });
  };
};

let resolvers: Shared.dep => mutation =
  dep => {
    "createCommandSequence": createCommandSequence,
    "uplinkCommandSequence": uplinkCommandSequence(dep),
  };