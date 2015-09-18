
var HelloWorldLayer = cc.Layer.extend({
    sprite:null,
    builder:null,
    ctor:function () {
        //////////////////////////////
        // 1. super init first
        this._super();

        //需要初始化
        mo.messageManager.init();

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

        var menu3 = new cc.MenuItemFont("打开扎金花界面", this.openZjhLayer, this);
        menu3.setFontSize(20);
        menu3.setPosition(0, 100);

        var menu = new cc.Menu(menu1, menu2, menu3);
        this.addChild(menu);


        return true;
    },
    connection : function(sender){
        mo.nativeHelper.setPacketAssembler(function(strbase64, msgId){
            console.log("准备开始解析消息\nstrbase64:" + strbase64 + "\nmsgId:" + msgId);
            mo.messageManager.recvMsg(strbase64, msgId);
        });
        mo.nativeHelper.test();
        mo.nativeHelper.startSendMsg();
    },
    sendMsg : function(sender){
        mo.messageManager.sendLoLoginFromHTTP("8c53d6a1d685c72414d655d21f6c43c5");
    },
    openZjhLayer : function(sender){
        this.getParent().addChild(new ZjhTableLayer());
        this.getParent().removeChild(this);
    }
});

var HelloWorldScene = cc.Scene.extend({
    onEnter:function () {
        this._super();
        var layer = new HelloWorldLayer();
        this.addChild(layer);

        mo.mainZjhScene = this;
    }
});

mo.nativeHelper = cc.NativeHelper.singleton();
