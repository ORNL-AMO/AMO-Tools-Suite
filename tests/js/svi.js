const test = require('tap').test
    , testRoot = require('path').resolve(__dirname, '../../')
    , bindings = require('bindings')({ module_root: testRoot, bindings: 'svi' });

function rnd(value) {
    return Number(Math.round(value + 'e' + 2) + 'e-' + 2);
}

test('State Point Analysis SVIXX/VoK', function (t) {
    t.plan(29);
    t.type(bindings.svi, 'function');

    let validate = function(results, expected) {
        t.equal(rnd(results.TotalAreaClarifier), rnd(expected[0]));
        t.equal(rnd(results.SurfaceOverflow), rnd(expected[1]));
        t.equal(rnd(results.AppliedSolidsLoading), rnd(expected[2]));
        t.equal(rnd(results.RasConcentration), rnd(expected[3]));
        t.equal(rnd(results.UnderFlowRateX2), rnd(expected[4]));
        t.equal(rnd(results.UnderFlowRateY1), rnd(expected[5]));
        t.equal(rnd(results.OverFlowRateX2), rnd(expected[6]));
        t.equal(rnd(results.OverFlowRateY2), rnd(expected[7]));
        t.equal(rnd(results.StatePointX), rnd(expected[8]));
        t.equal(rnd(results.StatePointY), rnd(expected[9]));

        t.equal(results.graphData[39][0], rnd(expected[10]));
        t.equal(rnd(results.graphData[39][1]), rnd(expected[11]));
        t.equal(results.graphData[150][0], rnd(expected[12]));
        t.equal(rnd(results.graphData[150][1]), rnd(expected[13]));

        console.log(" ");
        console.log("Begin Graph Data Points");
        console.log(JSON.stringify(results.graphData));
        console.log("End Graph Data Points");
    };

    /*************
    SVIParameter
        SVISN : 0
        SVIGN : 1
        SVIGS : 2
        SVISS : 3
        VoK   : 4
     *************/

    let results = bindings.svi({sviParameter : 1, sviValue: 0.150000, numberOfClarifiers: 1, areaOfClarifier: 930, MLSS: 0.0025, influentFlow: 1892705, rasFlow: 788627, sludgeSettlingVelocity: 1});
    validate(results, [930, 2035.17, 7.20788, 0.0085, 8.5000006, 7.20788, 3.8057908, 7.7454186, 2.5000, 5.0879167, 3.9, 5.21, 15, 0.16]);

    results = bindings.svi({sviParameter : 4, sviValue: 0.6000, numberOfClarifiers: 2, areaOfClarifier: 84.3486, MLSS: 0.0025, influentFlow: 157725, rasFlow: 110408, sludgeSettlingVelocity: 8.998});
    validate(results, [168.6971, 934.9626, 3.973591, 0.006071, 6.07142857, 3.97359117, 7.37591695, 6.89620669, 2.5000, 2.33740657, 3.9, 3.38, 15, 0.02]);
});