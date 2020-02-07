let testNumber = 1;
let validTests = 0;
let invalidTests = 0;

function assertNumber(num1, num2) {
    return Math.abs(num1 - num2) < .005;
}

function testNumberValue(testVal, expectedValue, testName){
    const testElement = document.createElement('div');
    let testBool = assertNumber(testVal, expectedValue);
    if(testBool == true){
        testElement.className = 'valid';
        validTests++;
    }else{
        testElement.className = 'invalid';
        invalidTests++;
    }
    testElement.innerHTML = testName + ": " + testBool;
    document.body.appendChild(testElement);
    const resultsElement = document.createElement('div');
    resultsElement.innerHTML = 'Expected: ' + expectedValue + ', Actual: ' + testVal;
    resultsElement.className = 'expected-div';
    document.body.appendChild(resultsElement);
}

function logTestData(){
    const finishLabel = document.createElement('label');
    finishLabel.innerHTML = "Testing Results";
    document.body.appendChild(finishLabel);
    const testElement = document.createElement('div');
    testElement.innerHTML = validTests + "/" + (validTests+invalidTests) + " tests passing";
    document.body.appendChild(testElement);
}