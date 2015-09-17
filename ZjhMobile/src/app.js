
var HelloWorldLayer = cc.Layer.extend({
    sprite:null,
    ctor:function () {
        //////////////////////////////
        // 1. super init first
        this._super();

        /////////////////////////////
        // 2. add a menu item with "X" image, which is clicked to quit the program
        //    you may modify it.
        // ask the window size
        var size = cc.winSize;


        //var storagePath = (jsb.fileUtils ? jsb.fileUtils.getWritablePath() : "./");
        //var filename = storagePath + "Person.proto";
        //console.log(filename);

        //var protoString = jsb.fileUtils.getStringFromFile("res/packets.txt");

        var menu1 = new cc.MenuItemFont("连接服务器", this.connection, this);
        menu1.setFontSize(30);
        menu1.setPosition(0, 0);

        var menu2 = new cc.MenuItemFont("发送测试消息", this.sendMsg, this);
        menu2.setFontSize(20);
        menu2.setPosition(0, 50);

        var menu = new cc.Menu(menu1, menu2);
        this.addChild(menu);


        return true;
    },
    connection : function(sender){
        mo.nativeHelper.setCallFunc(function(val){
            cc.log(val);
        });
        mo.nativeHelper.test();
    },
    sendMsg : function(sender){
        var builder = null;
        try {
            var protoString = jsb.fileUtils.getStringFromFile("res/packets.txt");
            builder = protobufjs.loadProto(protoString);
            //builder = protobufjs.loadProtoFile("res/packets.txt");
        } catch (e) {
            console.log("error");
            console.log(e + "error");
        } finally {
            console.log("finally");
        }
        var LoginRequest = builder.build("packet.LoginFromHTTPRequest");
        var myLoginRequest = new LoginRequest();

        myLoginRequest.cookie = "573a6a389c939199771f445692b4e37f";

        var buffer = myLoginRequest.encode();

        var string = "";
        for (var i = 0; i < buffer.view.length; i++){
            //console.log(buffer.view[i]);
            string += String.fromCharCode(buffer.view[i]);
        }
        var codeString = mo.nativeHelper.codeData(string);

        var arrayBuffer = buffer.toArrayBuffer();
        //console.log(myLoginRequest.toArrayBuffer() + "");
        console.log(myLoginRequest.toBase64());

        mo.nativeHelper.testSend(codeString);
        //mo.nativeHelper.testSend1(arrayBuffer);

        //var YourMessage = builder.build("packet.LoginFromHTTPRequest");
        //var myMessage = YourMessage.decode(arrayBuffer);
        //console.log(myMessage.password);
    },
    codeData : function(data){
        var key = new Array(71, 113, 127, 103, 67, 97, 73, 79, 107, 131, 61, 109, 59, 101, 89, 83);
        var keylenght = key.length;
        var datalenght = data.length;

        var result = "";
        for (var i = 0; i< datalenght; i++)
        {
            var temp = key[i % keylenght];
            var dataTemp = data.charCodeAt(i);
            var out = dataTemp ^ temp;
            console.log(i + ":" + out);
            result += String.fromCharCode(out);
        }
        return result;
    }
});

var HelloWorldScene = cc.Scene.extend({
    onEnter:function () {
        this._super();
        var layer = new HelloWorldLayer();
        this.addChild(layer);
    }
});

mo.nativeHelper = cc.NativeHelper.singleton();
