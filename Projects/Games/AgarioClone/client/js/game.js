"use strict"
// CONSTANTS:
const DIR_LEFT = 0
const DIR_RIGHT = 1
const DIR_UP = 2
const DIR_DOWN = 3

const SPEED = 5

const VISIBLE_WIDTH = document.body.clientWidth
const VISIBLE_HEIGHT = document.body.clientHeight

const FIELD_WIDTH = 2000
const FIELD_HEIGHT = 2000

// VARS

var username = prompt("Enter username")
var socket = new WebSocket("ws://localhost:8080/agario/" + username);

socket.onmessage = onMessage;
socket.onclose = onClose;

var field = document.getElementById("game-field")

field.width = VISIBLE_WIDTH
field.height = VISIBLE_HEIGHT

var ctx = field.getContext('2d');

var timer

var persons = new PersonsList() // Список персонажей
var my_person = null // Персонаж текущего пользователя

let DELAY = 70;

document.onkeydown = function(e) {
   switch (e.key) {
      case "ArrowUp":
         my_person.dirrection = DIR_UP
         break
      case "ArrowDown":
         my_person.dirrection = DIR_DOWN
         break
      case "ArrowLeft":
         my_person.dirrection = DIR_LEFT
         break
      case "ArrowRight":
         my_person.dirrection = DIR_RIGHT
         break
   }
}

function redraw() {
   ctx.clearRect(0, 0, field.width, field.height)
   let x0

   // Изменение координат в соотвествии с камерой
   if(FIELD_WIDTH - my_person.center.x < VISIBLE_WIDTH / 2) {
      x0 = FIELD_WIDTH - VISIBLE_WIDTH
   } else if(my_person.center.x < VISIBLE_WIDTH / 2) {
      x0 = 0
   } else {
      x0 = my_person.center.x - VISIBLE_WIDTH / 2
   }
   let y0
   if(FIELD_HEIGHT - my_person.center.y < VISIBLE_HEIGHT / 2) {
      y0 = FIELD_HEIGHT - VISIBLE_HEIGHT
   } else if(my_person.center.y < VISIBLE_HEIGHT / 2) {
      y0 = 0
   } else {
      y0 = my_person.center.y - VISIBLE_HEIGHT / 2
   }


   persons.toArray().forEach(function(item) {
      if(item.equals(my_person)) {
         item.specialDraw(ctx, x0, y0)
      } else {
         item.draw(ctx, x0, y0)
      }
   })

   persons.drawLeaders(ctx)
}

function move() {
   switch(my_person.dirrection) {
      case DIR_LEFT:
         if(my_person.center.x <= 0) break
         my_person.center.x -= SPEED
         break;
      case DIR_RIGHT:
         if(my_person.center.x >= FIELD_WIDTH) break
         my_person.center.x += SPEED
         break;
      case DIR_UP:
         if(my_person.center.y <= 0) break
         my_person.center.y -= SPEED
         break;
      case DIR_DOWN:
         if(my_person.center.y >= FIELD_HEIGHT) break
         my_person.center.y += SPEED
         break;
   }
   redraw()
   let msg = {"eventType": "COORDS_CHANGING", "person": my_person}
   socket.send(JSON.stringify(msg))
}

function onMessage(event) {
    let message = JSON.parse(event.data);
    let person = new Person(message.person, socket)

    switch (message.eventType) {
      case "MY_SPAWN":
         my_person = person
         timer = new Timer(move, DELAY);
         timer.start()
         // break опущен тк нужно продолжить спавн :)
      case "SPAWN":
         persons.add(person)
         break
      case "DEAD":
         console.log(message)
         persons.remove(person) // Удаляем из списка убитого персонажа
         if(person.equals(my_person)) {
            timer.stop()
            alert("You lose")
         }
         break
      case "COORDS_CHANGING":
         persons.change(person)
         break
      case "SIZE_CHANGING":
         persons.resize(person)
         DELAY = 70 + my_person.size*0.1
         break
      default:
         console.log(message)
         break
    }
    redraw()
}

function onClose() {
   alert("Server die")
   timer.stop()
}
