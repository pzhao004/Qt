var index=0,
    flag=true,
    pan;

function start(pan,x,y,wid,hei) {
    lineChartCanvas.height=hei;
    lineChartCanvas.width=wid;
    pan.strokeStyle = "#08b95a"; //设置画笔颜色
    pan.lineJoin = "round";      //设置画笔轨迹基于圆点拼接
    pan.lineWidth = 1;           //设置画笔粗细
    pan.beginPath();
    pan.moveTo(x,y);
    //index = setInterval(move,1);
}

function move(pan,x,y,wid,hei){
    x++;
    if(x < 100){

    }else{
        if(x >= wid - 100){

        }else{
            var z = Math.random()*280;
            if(y <= z){
                flag = true;
            }
            if((hei - y) <= z){
                flag = false;
            }
            if(flag){
                y+=5;
            }else{
                y-=5;
            }
        }
    }

    if(x === wid){
        pan.closePath();
        clearInterval(index);
        index = 0;
        x = 0;
        y = hei/2;
        flag = true;
        start(pan,x,y,index,wid,hei,flag);
    }
    pan.lineTo(x,y);
    pan.stroke();
}
