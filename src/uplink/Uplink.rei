type t;
let create: Shared.dep => t;
let start: (t, Schema.commandSequence) => unit;
let stop: t => unit;