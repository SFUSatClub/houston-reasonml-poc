type action =
  | UplinkStart(Schema.commandSequence)
  | UplinkSend(string)
  | UplinkAck(string)
  | UplinkTimeout(string)
  | UplinkStop;