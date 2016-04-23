package com.jd.wq.rc.mongospark;

import java.util.HashSet;
import java.util.Set;

import org.apache.hadoop.conf.Configuration;
import org.apache.spark.SparkConf;
import org.apache.spark.api.java.JavaPairRDD;
import org.apache.spark.api.java.JavaRDD;
import org.apache.spark.api.java.JavaSparkContext;
import org.apache.spark.api.java.function.Function;
import org.apache.spark.api.java.function.Function2;
import org.apache.spark.api.java.function.PairFunction;
import org.bson.BSONObject;
import org.bson.BasicBSONObject;

import com.mongodb.hadoop.MongoInputFormat;

import scala.Tuple2;

public class Connectiondb 
{

	//private static String MONGODB_HOST = "mongodb://ip:port/db.collection";
	private static String MONGODB_HOST = "mongodb://";
	public static String FieldQuery(String sFeild, String sStart, String sEnd)
	{
		return String.format("{\"%s\" : {\"$gt\": \"%s\", \"$lt\" : \"%s\" }}", sFeild, sStart, sEnd);
	}
	public static void main(String[] args) 
	{
		// Set configuration options for the MongoDB Hadoop Connector.
		Configuration mongodbConfig = new Configuration();
		// MongoInputFormat allows us to read from a live MongoDB instance.
		// We could also use BSONFileInputFormat to read BSON snapshots.
		mongodbConfig.set("mongo.job.input.format",
		                  "com.mongodb.hadoop.MongoInputFormat");
		// MongoDB connection string naming a collection to use.
		// If using BSON, use "mapred.input.dir" to configure the directory
		// where BSON files are located instead.
		String mongodbIp = args[0];
		String mongodbPort = args[1];
		String mongodbCollection = args[2];
		String mongodbUri = MONGODB_HOST + mongodbIp + ":" + mongodbPort + "/" + mongodbCollection;

		mongodbConfig.set("mongo.input.uri", mongodbUri);
		mongodbConfig.set("mongo.input.query", FieldQuery("stattime", "1460110205", "1460122220") );
		mongodbConfig.set("mongo.input.fields", "{\"actId\":1, \"materialId\":1, \"showCnt\":1, \"clickCnt\":1}");//default keep "_id"
		//mongodbConfig.set("mongo.input.query", "{\"showCnt\" : {\"$gt\": 4000}}");
		//mongodbConfig.set("mongo.input.query", "{\"stattime\" : {\"$gt\": \"1460110205\", \"$lt\" : \"1460110220\" }}");
		//mongodbConfig.set("mongo.input.query", String.format("{\"%s\" : {\"$gt\": \"%s\", \"$lt\" : \"%s\" }}", "stattime", "1460110205", "1460110220") );
		
		/*
		 * \" Insert a double quote character in the text at this point
		 *  db.bsheat.find().sort({"stattime":1})  1 to specify ascending order. -1 to specify descending order.
		 *  {"field" : {"$gt" : val, "$lt" : val}} extend json. like pythn dict
		 */
		
		// Create an RDD backed by the MongoDB collection.
		SparkConf conf = new SparkConf().setMaster("local").setAppName("TestConnection");
		JavaSparkContext sc = new JavaSparkContext(conf);
		//BSONObject
		
		JavaPairRDD<Object, BSONObject> documents = sc.newAPIHadoopRDD(
		    mongodbConfig,            // Configuration
		    MongoInputFormat.class,   // InputFormat: read from a live cluster.
		    Object.class,             // Key class
		    BSONObject.class          // Value class
		);
		//JavaRDD<BSONObject> documents = sc.newAPIHadoopRDD(mongodbConfig,MongoInputFormat.class, Object.class, BSONObject.class);
		
		
		
		JavaRDD<BSONObject> documents_1 = documents.map(
				new Function<Tuple2<Object,BSONObject>, BSONObject>() {
	                /**
					 * 
					 */
					private static final long serialVersionUID = 1L;

					public BSONObject call(Tuple2<Object,BSONObject> doc) throws Exception {
	                	doc._2.removeField("_id");
	                	return doc._2;
	                	
	                	/* tip1
	                	BasicBSONObject oRData1 = (BasicBSONObject) doc._2;
	                	Object odeleted = oRData1.removeField("_id"); // error return oRData1.removeField("_id");
	                	System.out.println(odeleted);
	                	return oRData1;
	                	*/

	                	/* tip2
	                	System.out.println(oRData1.remove("clickCnt")); 
	                	
	                	BasicBSONObject oRData = new BasicBSONObject();
	                	doc._2.removeField("_id");
	                	for(String sKey : doc._2.keySet())
	                	{
	                		//System.out.println(sKey);
	                		// _id, actId, materialId, showCnt, clickCnt
	                		if(sKey.equals("_id") == true)
	                		{
	                			continue;
	                		}
	                		else
	                		{
	                			oRData.put(sKey, doc._2.get(sKey));
	                		}
	                		
	                	}
	                	return oRData;
	                	*/
	                }
	            }
				);
		JavaPairRDD<BSONObject, BSONObject> documents_2 = documents_1.mapToPair(
				new PairFunction<BSONObject, BSONObject, BSONObject>() {
					/**
					 * 
					 */
					private static final long serialVersionUID = 1L;

					public scala.Tuple2<BSONObject,BSONObject> call(BSONObject t) throws Exception {
						BSONObject oKey = new BasicBSONObject();  // *key point basic -> herr*
						BSONObject oVal = new BasicBSONObject();
						for(String sField : t.keySet())
						{
							if(sField.equals("actId") == true || sField.equals("materialId") == true)
							{
								oKey.put(sField, t.get(sField));
							}
							else
							{
								oVal.put(sField, t.get(sField));
							}
							//System.out.println(oKey);
								
						}
						return new Tuple2<BSONObject, BSONObject>(oKey, oVal);
						
					};
				}
				);
		
		JavaPairRDD<BSONObject, BSONObject> documents_3 = documents.mapToPair(
				//auto generate param1
				new PairFunction<Tuple2<Object,BSONObject>, BSONObject, BSONObject>() {
					/**
					 * 
					 */
					private static final long serialVersionUID = 1L;

					public scala.Tuple2<BSONObject,BSONObject> call(scala.Tuple2<Object,BSONObject> t) throws Exception {
						BSONObject oKey = new BasicBSONObject();
						BSONObject oVal = new BasicBSONObject();
						for(String sField : t._2.keySet())
						{
							if(sField.equals("_id") == true)
							{
								continue;
							}
							if(sField.equals("actId") == true || sField.equals("materialId") == true)
							{
								oKey.put(sField, t._2.get(sField));
							}
							else
							{
								oVal.put(sField, t._2.get(sField));
							}
							//System.out.println(sField);
							
						}
						return new Tuple2<BSONObject, BSONObject>(oKey, oVal);
					};
				}

				
				);
		
		JavaPairRDD<BSONObject, BSONObject> documents_4 = documents_3.reduceByKey(
				new Function2<BSONObject, BSONObject, BSONObject>() {
					
					/**
					 * 
					 */
					private static final long serialVersionUID = 1L;

					@Override

					public BSONObject call(BSONObject v1, BSONObject v2) throws Exception {
						BSONObject oReduce = new BasicBSONObject();
						
						/*
						int clickCnt = 0;
						int showCnt = 0;
						clickCnt += new Double(String.valueOf(v1.get("clickCnt"))).intValue() + new Double(String.valueOf(v2.get("clickCnt"))).intValue() ;
						showCnt += new Double(String.valueOf(v1.get("showCnt"))).intValue() + new Double(String.valueOf(v2.get("showCnt"))).intValue() ;
						oReduce.put("clickCnt", clickCnt);
						oReduce.put("showCnt", showCnt);
						*/
						/*
						Set<String> key1 = v1.keySet();
						Set<String> key2 = v2.keySet();
						Set<String> key = new TreeSet<String>(key1);
						key.addAll(key2);
						System.out.println(key);
						for(String skey : key)
						{
							
						}
						*/
						Set<String> Fieldkey =  new HashSet<String>(v1.keySet());
						Fieldkey.addAll(v2.keySet());
						//System.out.println(Fieldkey);
						for(String sTempkey : Fieldkey)
						{
							//System.out.println(sTempkey);
							int iCntv1 = 0;
							int iCntv2 = 0;
							if(v1.get(sTempkey) != null)
							{
								String sCntv1 = String.valueOf(v1.get(sTempkey));  // v1
								iCntv1 = (sCntv1.length() == 0)?0:(new Double(sCntv1).intValue());
							}
							if(v2.get(sTempkey) != null)
							{
								String sCntv2 = String.valueOf(v2.get(sTempkey)); // v2
								iCntv2 = (sCntv2.length() == 0)?0:(new Double(sCntv2).intValue());
							}
							oReduce.put(sTempkey, iCntv1 + iCntv2);
						}
						//System.out.println(key);
						
						return oReduce;
					};
				}
				);
		
		JavaPairRDD<BSONObject, BSONObject> documents_5 = documents_4.mapToPair(
				new PairFunction<Tuple2<BSONObject,BSONObject>, BSONObject, BSONObject>() {
					/**
					 * use auto implement alt+/
					 */
					private static final long serialVersionUID = 1L;

					public scala.Tuple2<BSONObject,BSONObject> call(scala.Tuple2<BSONObject,BSONObject> t) throws Exception {
						//BSONObject oKey = new BasicBSONObject();
						//BSONObject oVal = new BasicBSONObject();
						t._2.put("materialId", t._1.get("materialId"));
						t._1.removeField("materialId");
						return new Tuple2<BSONObject, BSONObject>(t._1, t._2);
					};
				}
				);
		
		
			

		System.out.println(documents.collect());
		System.out.println(documents_1.collect());
		System.out.println(documents_2.collect());
		System.out.println(documents_3.collect()); // lazy eval
		System.out.println(documents_4.collect());
		System.out.println(documents_5.collect());
		sc.close();
		
	}
}
