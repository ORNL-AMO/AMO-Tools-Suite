function sludgeVolumeIndex(){
    let validate = function(results, expected) {
        testNumberValue(rnd(results.TotalAreaClarifier), rnd(expected[0]), "TotalAreaClarifier");
        testNumberValue(rnd(results.SurfaceOverflow), rnd(expected[1]), "SurfaceOverflow");
        testNumberValue(rnd(results.AppliedSolidsLoading), rnd(expected[2]), "AppliedSolidsLoading");
        testNumberValue(rnd(results.RasConcentration), rnd(expected[3]),"RasConcentration");
        testNumberValue(rnd(results.UnderFlowRateX2), rnd(expected[4]),"UnderFlowRateX2");
        testNumberValue(rnd(results.UnderFlowRateY1), rnd(expected[5]),"UnderFlowRateY1");
        testNumberValue(rnd(results.OverFlowRateX2), rnd(expected[6]),"OverFlowRateX2");
        testNumberValue(rnd(results.OverFlowRateY2), rnd(expected[7]),"OverFlowRateY2");
        testNumberValue(rnd(results.StatePointX), rnd(expected[8]),"StatePointX");
        testNumberValue(rnd(results.StatePointY), rnd(expected[9]),"StatePointY");

        testNumberValue(results.GraphData.get(39).SolidsConcentration, rnd(expected[10]),"GraphData => SolidsConcentration @ test index 39");
        testNumberValue(rnd(results.GraphData.get(39).SolidsFlux), rnd(expected[11]),"GraphData => SolidsFlux @ test index 39");
        testNumberValue(results.GraphData.get(150).SolidsConcentration, rnd(expected[12]),"GraphData => SolidsConcentration @ test index 39");
        testNumberValue(rnd(results.GraphData.get(150).SolidsFlux), rnd(expected[13]),"GraphData => SolidsFlux @ test index 39");

        let str = 'Data Dump<br/>Begin Graph Data Points<br/>[ ';
        for (let i = 0; i < results.GraphData.size(); i++) {
            if(i > 0) str += ',';
            str += '[' + results.GraphData.get(i).SolidsConcentration + ',' + results.GraphData.get(i).SolidsFlux.toFixed(2) + ']';
        }
        str += ' ]<br/>End Graph Data Points';

        logMessage(str);
    };

    logMessage('Sludge Volume Index: Test# 1', true);
    let instance = new Module.SludgeVolumeIndex(Module.SVIParameter.SVIGN, 0.150000, 1, 930, 0.0025, 1892705, 788627, 1);
    validate(instance.calculate(), [930, 2035.17, 7.20788, 0.0085, 8.5000006, 7.20788, 3.8057908, 7.7454186, 2.5000, 5.0879167, 3.9, 5.21, 15, 0.16]);

    logMessage('Sludge Volume Index: Test# 2', true);
    instance = new Module.SludgeVolumeIndex(Module.SVIParameter.VoK, 0.6000, 2, 84.3486, 0.0025, 157725, 110408, 8.998);
    validate(instance.calculate(), [168.6971, 934.9626, 3.973591, 0.006071, 6.07142857, 3.97359117, 7.37591695, 6.89620669, 2.5000, 2.33740657, 3.9, 3.38, 15, 0.02]);

    instance.delete();
}

sludgeVolumeIndex();