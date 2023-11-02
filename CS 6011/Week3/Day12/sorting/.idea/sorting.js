function selectionSort(arr, compareFn) {
    const len = arr.length;

    for (let i = 0; i < len; i++) {
        const minIndex = findMinLocation(arr, i, len, compareFn);
        if (minIndex !== i) { //if the min num is not i then we go to next step
            // Swap elements if necessary
            [arr[i], arr[minIndex]] = [arr[minIndex], arr[i]];
        }//sort the num with i and the min change to min num at the frist
    }

    return arr;
}

function findMinLocation(arr, start, end, compareFn) {
    let minIndex = start;
    for (let i = start + 1; i < end; i++) {
        if (compareFn(arr[i], arr[minIndex])) {
            minIndex = i;
        }//compare the i with min num,if i is the min then min = i
    }//and return the min number
    return minIndex;
}

// Comparator functions
function compareNumbers(a, b) {
    return a < b;
}

function compareStrings(a, b) {
    return a.toLowerCase() < b.toLowerCase();
}//use the lower case to compare the string

function comparePeopleByLastName(a, b) {
    return a.last.toLowerCase() < b.last.toLowerCase() ||
        (a.last.toLowerCase() === b.last.toLowerCase() && a.first.toLowerCase() < b.first.toLowerCase());
}

function comparePeopleByFirstName(a, b) {
    return a.first.toLowerCase() < b.first.toLowerCase() ||
        (a.first.toLowerCase() === b.first.toLowerCase() && a.last.toLowerCase() < b.last.toLowerCase());
}

// Test sorting functions

const numbersArray = [5, 3, 9, 1, 4];
console.log('Numbers Array:', selectionSort(numbersArray, compareNumbers));

const floatArray = [3.14, 1.56, 2.71, 0.99];
console.log('Float Array:', selectionSort([...floatArray], compareNumbers));

const stringsArray = ['apple', 'Banana', 'cherry', 'date'];
console.log('Strings Array:', selectionSort([...stringsArray], compareStrings));

const peopleArray = [
    { first: 'Terry', last: 'Tsao' },
    { first: 'Yuyao', last: 'Tu' },
    { first: 'Shane', last: 'Chen' },
];
console.log('People Array (by last name):', selectionSort([...peopleArray], comparePeopleByLastName));
console.log('People Array (by first name):', selectionSort([...peopleArray], comparePeopleByFirstName));