const canvas = document.getElementById('canvas');
const context = canvas.getContext('2d');

// Canvas control
const WIDTH = window.innerWidth; // TOTAL WIDHT OF SCREEN
const HEIGHT = window.innerHeight; // TOTAL HEIGHT OF SCREEN
canvas.width = WIDTH;
canvas.height = HEIGHT;

// QuickSort
let data = [] // arrayay to sort
let states = []; // animation
const arrayaySize = 100; // arrayay size

async function quickSort(array, start, end) {
    if (start >= end) {
        return;
    }
    let index = await partition(array, start, end);
    states[index] = -1;

    await Promise.all([
        quickSort(array, start, index - 1),
        quickSort(array, index + 1, end)
    ]);
}

async function partition(array, start, end) {
    for (let i = start; i < end; i++) {
        states[i] = 1;
    }

    let pivotValue = array[end];
    let pivotIndex = start;
    states[pivotIndex] = 0;
    for (let i = start; i < end; i++) {
        if (array[i] < pivotValue) {
            await swap(array, i, pivotIndex);
            states[pivotIndex] = -1;
            pivotIndex++;
            states[pivotIndex] = 0;
        }
    }
    await swap(array, pivotIndex, end);

    for (let i = start; i < end; i++) {
        if (i != pivotIndex) {
            states[i] = -1;
        }
    }

    return pivotIndex;
}

async function swap(array, a, b) {
    await sleep(50);
    let temp = array[a];
    array[a] = array[b];
    array[b] = temp;
}

function drawBar(arrayay, index) {
    const offset = (WIDTH / arrayaySize);
    const barWidth = (WIDTH / arrayaySize) - 1;
    const barHeight = HEIGHT -  arrayay[index];
    context.fillRect(index * offset, barHeight, barWidth, HEIGHT);
}

function draw() {
    context.clearRect(0, 0, WIDTH, HEIGHT);
    for (let i = 0; i < data.length; i++) {
        if (states[i] == 0) {
            context.fillStyle = '#f25760';
        } else if (states[i] == 1) {
            context.fillStyle = '#169FB7';
        } else {
            context.fillStyle = '#FFFFFF';
        }
        drawBar(data, i);
    }
    
    requestAnimationFrame(draw);
}

function rand(min, max) {
    return Math.floor(Math.random() * (max - min) + min);
}

function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

// Setup
function init() {
    for (let i = 0; i < arrayaySize; i++) {
        data.push(rand(1, HEIGHT - 10));
    }
    draw();
}

init();
quickSort(data, 0, data.length - 1);