/*************************************************/
/* Copied from bs-socket.io/ben's example */
module Path = {
  type pathT;
  [@bs.module "path"] [@bs.splice]
  external join : array(string) => string = "";
};

module Express = {
  type expressT;
  [@bs.module] external express : unit => expressT = "";
  [@bs.send] external use : (expressT, string) => unit = "use";
  [@bs.module "express"] external static : string => string = "static";
  type responseT;
  [@bs.send] external sendFile : (responseT, string, 'a) => unit = "sendFile";
  [@bs.send]
  external get : (expressT, string, ('a, responseT) => unit) => unit = "get";
};

module Http = {
  type http;
  [@bs.module "http"] external create : Express.expressT => http = "Server";
  [@bs.send] external listen : (http, int, unit => unit) => unit = "";
};


/*************************************************/
let app = Express.express();

let http = Http.create(app);

[@bs.val] external __dirname : string = "";

Js.log(__dirname);

Express.use(app, Express.static(Path.join([|__dirname, ".."|])));

Express.get(app, "/", (_req, res) =>
  Express.sendFile(res, Path.join([|__dirname, "index.html"|]), ())
);

/* let io = Socket.S.createWithHttp(http); */
/* let server = Socket.S.create(); */
/* Socket.S.onConnect(io, socket => */
/*   Socket.S.Socket.on(socket, message => Js.log(message)) */
/* ); */
let port = 3000;

Http.listen(http, port, () => Printf.printf("listening on *:%d\n", port));
