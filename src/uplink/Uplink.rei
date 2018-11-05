type t;
let create: Store.t(State.state, Action.action) => t;
let start: (t, Schema.commandSequence) => unit;
let stop: t => unit;