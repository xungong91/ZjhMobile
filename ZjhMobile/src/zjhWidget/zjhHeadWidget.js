/**
 * Created by gongxun on 15/9/18.
 */

var zjhHeadWidget = BaseWidget.extend({
    ctor: function () {
        this._super();

        var file = "res/zjhui/ccs_widget_game.json";
        cc.log("ccs.load : %s", file);
        var json = ccs.load(file);
        this.ccsNode = json.node;

        ccui.helper.seekWidgetByName(this.ccsNode, "Image_main").addTouchEventListener(this.touchBackEvent,this);

        ccui.helper.seekWidgetByName(this.ccsNode, "Button").addTouchEventListener(this.touchIntoEvent,this);

        this.addChild(this.ccsNode);
    }
});