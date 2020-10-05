(function($) {

    // table
    (function() {
        "use strict"

        function getButtonCells(btn) {
            let cells = btn.data('cells');
            if (!cells || !cells.length) {
                cells = [];
                switch (btn.data('type')) {
                    case 'sector':
                        let nums = sectors[btn.data('sector')];
                        for (var i = 0, len = nums.length; i < len; i++) {
                            cells.push(table_nums[nums[i]]);
                        }
                        return cells;
;
                    case 'num':
                    default:
                        nums = String(btn.data('num')).split(',');
                        for (var i = 0, len = nums.length; i < len; i++) {
                            cells.push(table_nums[nums[i]]);
                        }
                        btn.data('cells', cells);
                        return btn.data('cells');

                }
            }
            return cells;
        };

        // props
        var active = true,
            selectors = {
                roulette : '.roulette',
                num : '.num',
                sector : '.sector',
                table_btns : '.controlls .roulette-table-cell'
            },
            classes = {
                red : 'red',
                black : 'black',
                green : 'green',
                hover : 'hover'
            },
            numbers = {
                red : [],
                black : [],
                green : []
            },
            sectors = {
                '1' : [], // 1st row
                '2' : [], // 2nd row
                '3' : [], // 3rd row
                '4' : [], // 1st 12
                '5' : [], // 2nd 12
                '6' : [], // 3rd 12
                '7' : [], // 1 to 18
                '8' : [], // EVEN
                '9' : [], // RED
                '10' : [], // BLACK
                '11' : [], // ODD
                '12' : [], // 19 to 36
            },
            table_nums = {},
            table_sectors = {};

        // init
        $(selectors.num).each(function() {
            let $this = $(this),
                color,
                num = Number($this.text());
            // add to instances array
            table_nums[num] = $this;
            // add to colors array
            for (color in numbers) {
                if ($this.hasClass(classes[color])) {
                    numbers[color].push(num);
                    $this.data('color', color);
                }
            }
        })

        $(selectors.sector).each(function() {
            let $this = $(this),
                color;
            if ($this.hasClass(classes.red)) {
                color = 'red';
            } else if ($this.hasClass(classes.black)) {
                color = 'black';
            } else {
                color = 'sector';
            }
            $this.data('color', color);
            table_sectors[$this.data('sector')] = $this;
        });

        // sort numbers
        for (var color in numbers) {
            numbers[color].sort(function(a, b) { return a - b; });
        }

        // populate sectors
        for (var i = 1; i <= 36; i++) {
            // 1st row, 2nd row, 3rd row
            switch (i%3) {
                case 0:
                    sectors['1'].push(i);
                    break;
                case 1:
                    sectors['3'].push(i);
                    break;
                case 2:
                    sectors['2'].push(i);
                    break;
            }

            // 1st 12, 2nd 12, 3rd 12
            if (i <= 12) {
                sectors['4'].push(i);
            } else if (i <= 24) {
                sectors['5'].push(i);
            } else {
                sectors['6'].push(i);
            }

            // 1 to 18, 19 to 36
            if (i <= 18) {
                sectors['7'].push(i);
            } else {
                sectors['12'].push(i);
            }

            // ODD, EVEN
            if (i%2) {
                sectors['11'].push(i);
            } else {
                sectors['8'].push(i);
            }

            if (numbers.red.indexOf(i) !== -1) {
                sectors['9'].push(i);
            } else if (numbers.black.indexOf(i) !== -1) {
                sectors['10'].push(i);
            }
        }

        // buttons
        $(selectors.table_btns).hover(
            function() {
                hovering=1;
                if (active) {
                    var $this = $(this),
                        cells = getButtonCells($this);
                    for (var i = 0, len = cells.length; i < len; i++) {
                        cells[i].addClass(classes.hover);
                    }
                    var sector = $this.data('sector');
                    if (sector) {
                        table_sectors[sector].addClass(classes.hover);
                    }
                }
            },
            function() {
                hovering=0;
                const $this = $(this),
                    cells = getButtonCells($this);
                for (var i = 0, len = cells.length; i < len; i++) {
                    cells[i].removeClass(classes.hover);
                }
                const sector = $this.data('sector');
                if (sector) {
                    table_sectors[sector].removeClass(classes.hover);
                }
            }
        ).mousedown(function(e) {
            resetField();

            var numbers=[];
            if(typeof $(this).data('sector') != 'undefined'){

                if(e.button===2)changeBet(36+$(this).data('sector'),-1);
                else changeBet(36+$(this).data('sector'),+1);
            }
            else{
                numbers=$(this).data('num');

                if(typeof numbers.length ==='undefined')numbers=[numbers];
                else numbers=numbers.split(',');

                if(e.button===2)for(var i=0; i<numbers.length; i++)changeBet(numbers[i],-1);
                else for(var i=0;i<numbers.length;i++)changeBet(numbers[i],+1);
            }
        });
    })();

    document.oncontextmenu = function() {if(hovering)return false;};

})(jQuery);


let squares = new Array(48);
let divs = document.getElementsByTagName("div");

function init() {
    for (var i = 0; i < divs.length; i++) {
        var attr = divs[i].getAttribute("data-num");
        if (attr == null) {
            attr = divs[i].getAttribute("data-sector");
            if (attr == null) continue;
            var index = 36 + parseInt(attr);

            var rekt = divs[i].getBoundingClientRect();
            squares[index] = new Array(2);
            squares[index][1] = rekt.top + rekt.height / 4 - 5;
            squares[index][0] = rekt.left + rekt.width / 4 - 10;
        } else {
            if (attr.indexOf(',') !== -1) continue;
            var rekt = divs[i].getBoundingClientRect();
            squares[attr] = new Array(2);
            squares[attr][1] = rekt.top + rekt.height / 4;
            squares[attr][0] = rekt.left + rekt.width / 4 - 10;
        }
    }
}

init();
window.addEventListener("resize", init);


function getBets(){
    let array = [];
    bets.forEach(
        function (value, index) { 
            if (value !== 0) {
                if (index < 37) {
                    array.push(index);
                } else {
                    sectorsValues[index-37].forEach(
                        function (value, indexInSector) {
                            if (value !== 0) {
                                array.push(indexInSector);
                            }
                        }
                    );
                }
            }
        }
    );
    
    return array;
}

function resetField(){
    for(let i=0; i<bets.length; i++){
        bets[i]=0;
        if(chips[i]!=null)for(let j=0; chips[i].length>0; j++)document.body.removeChild(chips[i].pop());
    }

}


function rInt(min,max){
    return Math.floor(Math.random() * (max - min + 1)) + min;
}

var chips=new Array(48);

function changeBet(id, amount){

    if(amount>0){
        var img = document.createElement('img');
        img.src="image/chips.png";
        img.style.zIndex="0";
        img.style.position="absolute";

        var rX=rInt(-8,8);
        var rY=rInt(-8,8);

        img.style.left=(squares[id][0]+rX)+"px";
        img.style.top=(squares[id][1]+rY)+"px";

        img.style.width="30px";
        img.style.pointerEvents="none";

        document.body.appendChild(img);

        if(chips[id]==null)chips[id]=new Array(0);
        chips[id].push(img);
    }if(amount<0&&chips[id]!=null&&chips[id].length>0)document.body.removeChild(chips[id].pop());

    bets[id]+=amount;
    if(bets[id]<0)bets[id]=0;
}


var hovering=0;
var bets=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0];

var sectorsValues=[
    [0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1],//1rd column
    [0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0],//1nd column
    [0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0],//1st column
    [0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],//1st 11
    [0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0],//1nd 11
    [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1],//1rd 11
    [0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],//1 to 18
    [0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1],//even
    [0,1,0,1,0,1,0,1,0,1,0,0,1,0,1,0,1,0,1,1,0,1,0,1,0,1,0,1,0,0,1,0,1,0,1,0,1],//Red
    [0,0,1,0,1,0,1,0,1,0,1,1,0,1,0,1,0,1,0,0,1,0,1,0,1,0,1,0,1,1,0,1,0,1,0,1,0],//Black
    [0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0],//odd
    [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1] //19 to 16
];
