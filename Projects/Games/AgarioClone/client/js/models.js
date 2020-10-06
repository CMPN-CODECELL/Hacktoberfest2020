"use strict"

class Person {
   constructor(person_from_json, socket) {
      this.id = person_from_json.id
      this.username = person_from_json.username
      this.center = person_from_json.center
      this.color = person_from_json.color
      this.size = person_from_json.size
      this.dirrection = DIR_RIGHT
   }

   equals(person) {
      return person.id === this.id
   }

   specialDraw(ctx, x0, y0) { // Отрисовка владельца очереди
      this.draw(ctx, x0, y0, true)
      ctx.fillStyle = "#cf00ff"
      ctx.beginPath()

      let x = this.center.x - x0
      let y = this.center.y - y0


      ctx.arc(x,y, this.size+2, 0, 2 * Math.PI);
      ctx.stroke()
   }

   draw(ctx, x0, y0, ignore) {
      var x = this.center.x - x0
      var y = this.center.y - y0

      if(ignore != true && (x < 0 - persons.size || y < 0 - persons.size || x > VISIBLE_WIDTH + persons.size|| y > VISIBLE_HEIGHT + persons.size)) {
         return
      }

      ctx.fillStyle = this.color
      ctx.beginPath()
      ctx.arc(x, y, this.size, 0, 2 * Math.PI);
      ctx.fill()

      if(this.username == "mob") return

      ctx.fillStyle = "#000"
      let fontSize = 15*this.size/20
      ctx.font = fontSize + "px Arial";
      ctx.textAlign = "center";
      ctx.fillText(this.username, x, y + this.size + fontSize);
   }
}

class PersonsList {
   constructor() {
      this.persons = []
   }

   add(person) {
      this.persons.push(person)
   }

   getArrayIndex(person) {
      for(let i = 0; i < this.persons.length; i++) {
         if(this.persons[i].equals(person)) {
            return i;
         }
      }
   }

   remove(person) {
      let index = this.getArrayIndex(person)
      this.persons.splice(index,1)
   }

   change(person) {
      let index = this.getArrayIndex(person)
      this.persons[index].center = person.center
   }

   resize(person) {
      let index = this.getArrayIndex(person)
      this.persons[index].size = person.size
   }

   toArray() {
      return this.persons
   }

   drawLeaders(ctx) {
      ctx.fillStyle = "rgba(100,150,185,0.5)";
      ctx.rect(document.body.clientWidth - 400, 0, document.body.clientWidth, 0+300)
      ctx.fill()

      let leaders = []
      leaders.unshift([].concat(this.persons));

      function compare(a,b) {
        if (a.size > b.size)
          return -1;
        if (a.size < b.size)
          return 1;
        return 0;
      }

      this.persons.sort(compare)

      ctx.fillStyle = "#000"
      ctx.font = "20px Arial";
      ctx.textAlign = "center";

      ctx.fillText("LEADERS: ", document.body.clientWidth - 260, 40);

      ctx.font = "15px Arial";
      this.persons.forEach(function(item, i) {
         if(item.username != "mob") {
            ctx.fillText(item.username + "[" + item.id + "] - " + item.size,
                  document.body.clientWidth - 260, 60 + 20*i);
         }
         if(i == 10) {
            return;
         }
      })


   }
}

class Timer {
   constructor(clb, timeout) {
        this.clb = clb;
        this.timeout = timeout;
        this.stopTimeout = null;
        this.precision = -1;
     }

    start() {
        let me = this;
        let now = new Date();
        if(me.precision === -1) {
            me.precision = now.getTime()
        }
        me.stopTimeout = setTimeout(function(){
            me.start()
        }, me.precision - now.getTime() + me.timeout)
        me.precision += me.timeout
        me.clb()
    }

    stop() {
        clearTimeout(this.stopTimeout)
        this.precision = -1
    }
}
