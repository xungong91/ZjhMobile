var app = null;

(function e(t,n,r){function s(o,u){if(!n[o]){if(!t[o]){var a=typeof require=="function"&&require;if(!u&&a)return a(o,!0);if(i)return i(o,!0);var f=new Error("Cannot find module '"+o+"'");throw f.code="MODULE_NOT_FOUND",f}var l=n[o]={exports:{}};t[o][0].call(l.exports,function(e){var n=t[o][1][e];return s(n?n:e)},l,l.exports,e,t,n,r)}return n[o].exports}var i=typeof require=="function"&&require;for(var o=0;o<r.length;o++)s(r[o]);return s})({1:[function(require,module,exports){
/**
 * Created by gongxun on 15/9/17.
 */

// 此处引用模块跟`nodejs`里一样
app = require('./calcu.js')

console.log(app.add(8, 5));
console.log(app.subtract(8, 5));
},{"./calcu.js":2}],2:[function(require,module,exports){
/**
 * Created by gongxun on 15/9/17.
 */

var calcu = {
    add: function(a, b){
        return a + b;
    },
    subtract: function(a, b){
        return a - b;
    }
}
// 此处对外导出模块功能
module.exports = calcu;
},{}]},{},[1]);
