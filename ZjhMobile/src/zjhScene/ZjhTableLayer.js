/**
 * Created by gongxun on 15/9/18.
 */

var ZjhTableLayer = ZjhBaseLayer.extend({
    ctor: function () {
        this._super();

        var file = "res/zjhui/ccs_zjhTableLayer.json";
        cc.log("ccs.load : %s", file);
        var json = ccs.load(file);
        this.ccsNode = json.node;
        this.addChild(this.ccsNode);
        this.resetSize(this.ccsNode);

        //setting button
        var Button_setting = ccui.helper.seekWidgetByName(this.ccsNode, "Button_setting");
        Button_setting.addTouchEventListener(this.touchEventSetting,this);
    },
    touchEventSetting: function (sender, type) {
        if (type == ccui.Widget.TOUCH_ENDED){
            mo.roomMsgHelper.showMsg("马上开始进入设置模式");
        }
    }
});