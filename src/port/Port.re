type t;
type buffer = Node_buffer.t;

[@bs.send]
external onData : (t, [@bs.as "data"] _, buffer => unit) => unit = "on";

[@bs.send]
external write :
  (t, [@bs.unwrap] [ | `Str(string) | `Buf(buffer) | `Arr(array(int))]) =>
  bool =
  "write";