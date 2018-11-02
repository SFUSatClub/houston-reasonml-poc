open Schema;

type root;

[@bs.val] [@bs.module "./helpers"]
external readJsonFile : string => Js.Promise.t(commandSequence) = "";

[@bs.val] [@bs.module "./helpers"]
external writeJsonFile : (string, commandSequence) => Js.Promise.t(string) =
  "";

[@bs.val] [@bs.module "./helpers"]
external injectIdToObjTree : commandSequenceInput => commandSequence = "";

type mutation = {
  .
  "createCommandSequence":
    (root, {. "sequence": commandSequenceInput}) =>
    Js.Promise.t(commandSequence),
  "executeCommandSequence": (root, {. "id": string}) => Js.Promise.t(bool),
};

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