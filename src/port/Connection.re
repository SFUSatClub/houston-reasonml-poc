type buffer = Port.buffer;

/*
 Connection expects an Encoder.encode to return a value of type enc.
 enc is a type that models what a SerialPort port expects
 */
type enc =
  | Str(string)
  | Arr(array(int))
  | Buf(buffer);

module type Encoder = {type t; let encode: t => enc;};
module type Decoder = {type t; let decode: buffer => t;};

/*
 Make is a functor. Given a specific Encoder and Decoder modules it creates a Connection module.
 You can then create a value of type Connection by calling the create function.
 */

module type S =
  (Enc: Encoder, Dec: Decoder) =>
  {
    type t;
    type e = Enc.t;
    type d = Dec.t;
    type p = Port.t;

    type unsubscribe = unit => unit;

    let create: p => t;
    let write: (t, e) => bool;
    let subscribe: (t, d => unit) => unsubscribe;
    let listen: t => unit;
  };

module Make: S =
  (Enc: Encoder, Dec: Decoder) => {
    type e = Enc.t;
    type d = Dec.t;
    type p = Port.t;

    type observer = {
      id: int,
      f: Dec.t => unit,
    };

    type t = {
      port: Port.t,
      observerIncId: ref(int),
      observers: ref(list(observer)),
    };

    type unsubscribe = unit => unit;

    let create = port => {port, observers: ref([]), observerIncId: ref(0)};

    let write = (link, data) =>
      switch (Enc.encode(data)) {
      | Str(string) => Port.write(link.port, `Str(string))
      | Arr(array) => Port.write(link.port, `Arr(array))
      | Buf(buffer) => Port.write(link.port, `Buf(buffer))
      };

    let notify = ({observers}, data) =>
      List.iter(obs => obs.f(data), observers^);

    let listen = link =>
      Port.onData(link.port, buffer => buffer |> Dec.decode |> notify(link));

    let subscribe = ({observerIncId, observers}, f) => {
      let listener = {id: observerIncId^, f};
      observers := [listener, ...observers^];

      let unsubscribe = () =>
        observers := List.filter(l => l.id != observerIncId^, observers^);

      observerIncId := observerIncId^ + 1;

      unsubscribe;
    };
  };

module MockEncoder = {
  type t = string;
  let encode = s => Str(s);
};

module MockDecoder = {
  type t = string;
  let decode = Node_buffer.toString;
};

module Con = Make(MockEncoder, MockDecoder);