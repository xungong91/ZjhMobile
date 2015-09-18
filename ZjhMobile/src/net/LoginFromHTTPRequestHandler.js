/**
 * Created by gongxun on 15/9/18.
 */

var LoginFromHTTPRequestHandler = function(){
    var that = new baseMessageHandler();

    that.handler = function(strbase64, msgId){
        that.loadMessage(strbase64, msgId);

        console.log("------------------------------------");
        console.log(that.protobufMessage.user.nickname);
        console.log(that.protobufMessage.session_id);
        console.log("------------------------------------");
    };

    return that;
};