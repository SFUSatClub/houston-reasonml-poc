open Schema;

[@bs.val] [@bs.module "./index"]
external readCommandSequence : string => Js.Promise.t(commandSequence) =
  "readJsonFile";

[@bs.val] [@bs.module "./index"]
external writeCommandSequence :
  (string, commandSequence) => Js.Promise.t(string) =
  "writeJsonFile";

[@bs.val] [@bs.module "./index"]
external injectSequenceAndCommandIds : commandSequenceInput => commandSequence =
  "";