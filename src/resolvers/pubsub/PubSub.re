type t;
type stream;

[@bs.send]
external publishState : (t, [@bs.as "STATE"] _, SchemaState.state) => unit =
  "publish";

[@bs.send] external asyncIterator : (t, string) => stream = "";
