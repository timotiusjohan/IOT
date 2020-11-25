import 'package:flutter/material.dart';
import 'package:firebase_database/firebase_database.dart';

void main() {
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: dataLamp(),
    );
  }
}

class dataLamp extends StatefulWidget {

  @override
  State createState() {
    return stateLamp();
  }
}

class stateLamp extends State<dataLamp> {
  final referenceDatabase = FirebaseDatabase.instance;

  TextEditingController rangeC = TextEditingController();

  String a,b,c;


  Future<String> getCurValue() async {
    String result = (await FirebaseDatabase.instance.reference().child("Node1/curValue").once()).value;
    setState(() {
      b=result;
    });
    print(result);
    return result;
  }

  Future<String> getCurState() async {
    String result = (await FirebaseDatabase.instance.reference().child("Node1/state").once()).value;
    setState(() {
      c=result;
    });
    print(result);
    return result;
  }

  Future<String> getCurRange() async {
    String result = (await FirebaseDatabase.instance.reference().child("Node1/rangeValue").once()).value;
    setState(() {
      a=result;
    });
    print(result);
    return result;
  }




  Widget buildItem(Map a){
      return Text(a["curValue"]);
  }



  @override
  Widget build(BuildContext context) {
    final ref = referenceDatabase.reference().child('Node1');
    getCurValue();
    getCurState();
    getCurRange();
    return Scaffold(
      appBar: AppBar(
        title: Text("Small Smart Home"),
      ),
      body: Column(
        children: <Widget>[
          TextField(
            controller: rangeC,
            decoration: InputDecoration(hintText: "range"),
          ),
          RaisedButton(
            child: Text("Set Range"),
            onPressed: (){
              ref.child('rangeValue').set(rangeC.text).asStream();
            },
          ),
          Text("Current Range: "+a),
          Text("Current Value: "+b),
          Text("State Lampu: "+c),
        ],
      ),
    );
  }
}