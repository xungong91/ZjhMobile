/**
 * Created by gongxun on 15/9/18.
 */

var baseMessageHandler = function(){
    var that = {};

    that.protobufMessage = null;

    that.loadMessage = function(strbase64, msgId){
        var messageBuilder = mo.messageManager.builder.build(mo.messageManager.packetName[msgId]);
        that.protobufMessage = messageBuilder.decode64(strbase64);
    };

    return that;
};