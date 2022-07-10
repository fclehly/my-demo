console.log("hello")
console.debug("hello")
console.warn("hello")
console.error("hello")

// 递归示例
//斐波那契
var fib = function(i) {
    if (i <= 1) {
        return 1
    }
    return fib(i - 1) + fib(i - 2)
}
console.log(fib(10))

// foreach示例
var  a = ['a', 2, 3]
a.forEach(function(i, v) {
    console.log(i, v)
})