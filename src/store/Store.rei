type t('s, 'a);
type unsubscribe = unit => unit;

let create: (('s, 'a) => 's, 's) => t('s, 'a);
let dispatch: (t('s, 'a), 'a) => unit;
let getState: t('s, 'a) => 's;
let subscribe: (t('s, 'a), 's => unit) => unsubscribe;