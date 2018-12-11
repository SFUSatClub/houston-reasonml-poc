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

module type S = {
  type t;
  type e;
  type d;

  let create: Port.t => t;
  let write: (t, e) => bool;
  let subscribe: (t, d => unit) => Shared.unsubscribe;
  let listen: t => unit;
};

module Make =
       (Enc: Encoder, Dec: Decoder)
       : (S with type e := Enc.t and type d := Dec.t) => {
  type observer = {
    id: int,
    f: Dec.t => unit,
  };

  type t = {
    port: Port.t,
    observerIncId: ref(int),
    observers: ref(list(observer)),
  };

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

module MockedConnection =
  Make(
    {
      type t = string;
      let encode = s => Str(s);
    },
    {
      type t = string;
      let decode = Node_buffer.toString;
    },
  );