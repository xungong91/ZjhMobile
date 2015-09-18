/**
 * Created by gongxun on 15/8/5.
 */

var roomMsgSprite = cc.Sprite.extend({
    msg : null,

    ctor: function () {
        this._super("res/moveto_msg.png");

        this.setPosition(mo.curSize.x / 2, mo.curSize.y / 2);

        var delay = cc.delayTime(1.6);
        var moveBy = cc.moveBy(0.3, cc.p(0, 150));
        this.runAction(cc.sequence(delay, moveBy));

        this.schedule(this.onceCallBack, 2.8, 1);
    },
    onExit: function () {
        this._super();
    },
    onEnter: function () {
        this._super();
    },
    setMsg : function (msg){
        this.msg = new cc.LabelTTF.create("0%", "Arial", 24);
        this.msg.color = cc.color(255, 255, 0, 255);
        this.msg.x = 338;
        this.msg.y = 27.5;
        this.msg.string = msg;
        this.addChild(this.msg);
    },
    onceCallBack: function(){
        mo.mainZjhScene.removeChild(this);
    },
});

var roomMsgHelper = function (){
    var that = {};

    that.showMsg = function (msg){
        var sprite = new roomMsgSprite();
        sprite.setMsg(msg);
        mo.mainZjhScene.addChild(sprite, 10);
    };

    return that;
}

mo.roomMsgHelper =  new roomMsgHelper();