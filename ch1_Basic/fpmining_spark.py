#
# Licensed to the Apache Software Foundation (ASF) under one or more
# contributor license agreements.  See the NOTICE file distributed with
# this work for additional information regarding copyright ownership.
# The ASF licenses this file to You under the Apache License, Version 2.0
# (the "License"); you may not use this file except in compliance with
# the License.  You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

from __future__ import print_function

import sys
import commands
from operator import add

from pyspark import SparkContext
from pyspark.mllib.fpm import FPGrowth



def GetFreqItems(freq, outputdir):
    """
    :param freq: list[namedtuple("FreqItemset", ["items", "freq"])]
    :return:
    """
    #1 get prob and union prob
    dProb = {}
    dUnionProb = {}
    for t in freq:
        if(len(t.items) == 1):
            dProb[t.items[0]] = t.freq
        elif (len(t.items) > 1):
            tUnion = tuple(t.items)
            dUnionProb[tUnion] = t.freq
        else:
            continue
    #2 compute p(b|a)
    pBuyandBuy = []
    for union in dUnionProb:
        for item in union:
            if(item in dProb):
                ProbAB = round( (int(dUnionProb[union]) + 0.0) / int(dProb[item]), 2 )
                relation = [u for u in union if u != item]
                pBuyandBuy.append([item, relation, str(ProbAB)])
    with open(outputdir, 'w') as f:
        for i in pBuyandBuy:
            output = i[0] + '|' + ','.join(i[1]) + '|' + i[2] + '\n'
            f.write(output)
    cmd_put = "hadoop fs -put " + outputdir + " /test"
    cmd_rm = "hadoop fs -rm /test/" + outputdir.split('/')[-1]
    (iRet, RetInfo) = commands.getstatusoutput(cmd_put)
    if(iRet != 0):
        commands.getstatusoutput(cmd_rm)
        commands.getstatusoutput(cmd_put)




if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("Usage: fpmining_spark <infile> miniSupport(0,1) <outfile>", file=sys.stderr)
        exit(-1)
    sc = SparkContext(appName="PythonFpMining")
    #input pre-process
    data = sc.textFile(sys.argv[1], 1)
    fSupport = float(sys.argv[2])
    outDir = sys.argv[3]

    #data pre-process
    transactions = data.map(lambda line: list( set(line.strip().split(',')) ) )
    new_trans = transactions.filter(lambda t:len(t) > 1)

    #FPGrowth
    model = FPGrowth.train(new_trans, minSupport=fSupport, numPartitions=10)
    result = model.freqItemsets().collect()
    #for fi in result:
    #    print(fi.items, fi.freq)
    sc.stop()
    GetFreqItems(result, outDir)


