/**
 *  动态显示当前时间
 */
function showDateTime(){
    var sWeek=new Array("日","一","二","三","四","五","六");  //声明数组存储一周七天
    var myDate=new Date(); //获取当天日期
    var sYear=myDate.getFullYear(); //获取年
    var sMonth=myDate.getMonth()+1; //获取月
    var sDate=myDate.getDate(); //获取日
    var sDay=sWeek[myDate.getDay()]; //根据得到的数字星期,利用数组转化为星期
    var h=myDate.getHours(); //获取小时
    var m=myDate.getMinutes(); //获取分钟
    var s=myDate.getSeconds(); //获取秒
    //输入日期和星期
    document.getElementById("date").innerHTML=(sYear+"年"+sMonth+"月"+sDate+"日"+"星期"+sDay+"<br/>");
    h = formatTwoDigits(h);  //格式化小时,如果不足两位在前面补0
    m = formatTwoDigits(m); //格式化分钟,如果不足两位在前面补0
    s = formatTwoDigits(s); //格式化秒钟后,如果不足两位在前面补0
    //显示时间
    document.getElementById("msg").innerHTML=(h+":"+m+":"+s+"<br/>");
    setTimeout("showDateTime()",1000);//每秒执行一次showDateTime函数
}
window.onload=showDateTime;//在整个页面加载完成后执行此函数
//如果输入数是一位数,则在十位上补0
function formatTwoDigits(s) {
    if (s<10)
        return "0"+s;
    else
        return s;
}
