Js.log("Hello, BuckleScript and Reason!");

module Client = BsSocket.Client.Make(Message);

let client = Client.create();

Client.emit(client, "hi from client");
