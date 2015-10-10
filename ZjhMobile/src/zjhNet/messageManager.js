/**
 * Created by gongxun on 15/9/18.
 */

var messageManager = function(){
    var that = {};

    this.builder = null;

    that.msgName = {
        7:"packet.LoginFromHTTPRequest"
    };

    that.packetName = {
        2:"packet.LoginResponse",
        22:"packet.ActivityEvent"
    };

    that.init = function(){
        try {
            if(cc.sys.isNative) {
                var protoString = jsb.fileUtils.getStringFromFile("res/packets_zjh.txt");
                this.builder = protobufjs.loadProto(protoString);
            }else{
                this.builder = protobufjs.loadProtoFile("res/packets_zjh.txt");
            }

        } catch (e) {
            console.log("init protobuf error");
        }
    };

    that.recvMsg = function(strbase64, msgId){
        if (msgId == 2){
            var messageHandler = new LoginFromHTTPRequestHandler();
            messageHandler.handler(strbase64, msgId);
        }
    };

    that.sendMsg = function(proto, msgId)
    {
        var buffer = proto.encode();
        var string = "";
        for (var i = 0; i < buffer.view.length; i++)
        {
            string += String.fromCharCode(buffer.view[i]);
        }

        mo.nativeHelper.sendJsMsg(string, msgId);
    };

    that.sendLoLoginFromHTTP = function(cookie){
        /*
        var msgId = 7;
        var LoginRequest = this.builder.build(that.msgName[msgId]);
        var myLoginRequest = new LoginRequest();

        myLoginRequest.cookie = cookie;
        */

        var msgId = 1;
        var LoginRequest = this.builder.build(that.msgName[msgId]);
        var myLoginRequest = new myLoginRequest();
        myLoginRequest.username = "test01";
        myLoginRequest.password = hex_md5("123456");

        that.sendMsg(myLoginRequest, msgId);
    };

    //进入牌桌
    that.sendJoinFreeZJH = function(rule, rank)
    {
        var msgID = 7;
        var JoinFreeZJHRequest = this.builder.build("packet_zjh.JoinFreeZJHRequest");
        var request2 = new JoinFreeZJHRequest();
        request2.session_id = "12345678987654321";
        request2.rule = 0;
        request2.rank = 0;

        that.sendMsg(request2, msgID);
    };

    return that;
};

mo.messageManager = new messageManager();
mo.messageHandle = mo.messageHandle || {};