/**
 * Created by gongxun on 15/9/18.
 */

var ZjhBaseLayer = cc.LayerGradient.extend({
    ccsNode : null,

    ctor: function () {
        if (arguments.length === 0) {
            this._super(cc.color(0, 0, 0, 255), cc.color(0, 0, 0, 255));
        } else {
            this._super.apply(this, arguments);
        }
    },
    onExit: function () {
        ccs.armatureDataManager.clear();
        ccs.sceneReader.clear();
        ccs.actionManager.clear();
        ccs.uiReader.clear();
        this._super();
    },
    loadCocostudio : function(){

    },
    resetSize: function (node) {
        node.setContentSize(mo.curSize.x, mo.curSize.y);
        ccui.helper.doLayout(node);
        console.log(mo.curSize.x);
        console.log(mo.curSize.y);
    }
});