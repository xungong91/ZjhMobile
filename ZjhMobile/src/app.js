
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

        //mo.nativeHelper.setCallFunc(function(val){
        //    cc.log(val);
        //});
        //mo.nativeHelper.test();

        console.log(app.add(10, 12));

        //var storagePath = (jsb.fileUtils ? jsb.fileUtils.getWritablePath() : "./");
        //var filename = storagePath + "Person.proto";
        //console.log(filename);

        var protoString = jsb.fileUtils.getStringFromFile("res/packets_zjh.txt");

        var builder = null;
        try {
            builder = protobufjs.loadProto(protoString)
        } catch (e) {
            console.log("error");
            console.log(e + "error");
        } finally {
            console.log("finally");
        }
        var LoginRequest = builder.build("packet_zjh.LoginRequest");
        var myLoginRequest = new LoginRequest();

        myLoginRequest.username = "xungong";
        myLoginRequest.password = "a123456";

        console.log(myLoginRequest.username)

        return true;
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
