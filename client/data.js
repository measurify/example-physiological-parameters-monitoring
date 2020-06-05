


$(document).ready(function() {
    $.ajax({
        type: "GET",       
        url: "http://test.atmosphere.tools/v1/measurements",
        data: {filter: "{\"thing\":\"mario.rossi\"}", page : 1, limit :10},
        headers: {
            "Content-type" : "application/json",
            "Authorization": "JWT eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJfaWQiOiI1ZGQyNWFjZmVkNzA2ODJhOGQxMTQzNGEiLCJ1c2VybmFtZSI6InB1bHNlLXNlbnNvci11c2VyLXVzZXJuYW1lIiwidHlwZSI6InByb3ZpZGVyIiwiaWF0IjoxNTc1NjUzNDg0LCJleHAiOjE1NzU2NTUyODR9.ciC3XHTSHe0Zany0PkZ1HXYr5mVF01WaWQwW0z3aFbU",
            "charset": "UTF-8"
          },
            success: function(response){  
              //alert(response);  
        }
    })

    .then(function(response) {
      console.log(response);

        var o = response;
        console.log(o);
       $('.user').append(o.docs[0].thing); 
       $('.value0PA').append(o.docs[0].samples[0].values[0]);
       $('.value1PA').append(o.docs[0].samples[1].values[0]);
       $('.value2PA').append(o.docs[0].samples[2].values[0]);
       $('.value3PA').append(o.docs[0].samples[3].values[0]);
       $('.value4PA').append(o.docs[0].samples[4].values[0]);
       $('.value5PA').append(o.docs[0].samples[5].values[0]);
       $('.value6PA').append(o.docs[0].samples[6].values[0]);
       $('.value7PA').append(o.docs[0].samples[7].values[0]);
       $('.value8PA').append(o.docs[0].samples[8].values[0]);
       $('.value9PA').append(o.docs[0].samples[9].values[0]);
       $('.value0IBI').append(o.docs[1].samples[0].values[0]);
       $('.value1IBI').append(o.docs[1].samples[1].values[0]);
       $('.value2IBI').append(o.docs[1].samples[2].values[0]);
       $('.value3IBI').append(o.docs[1].samples[3].values[0]);
       $('.value4IBI').append(o.docs[1].samples[4].values[0]);
       $('.value5IBI').append(o.docs[1].samples[5].values[0]);
       $('.value6IBI').append(o.docs[1].samples[6].values[0]);
       $('.value7IBI').append(o.docs[1].samples[7].values[0]);
       $('.value8IBI').append(o.docs[1].samples[8].values[0]);
       $('.value9IBI').append(o.docs[1].samples[9].values[0]);
       $('.value0BPM').append(o.docs[2].samples[0].values[0]);
       $('.value1BPM').append(o.docs[2].samples[1].values[0]);
       $('.value2BPM').append(o.docs[2].samples[2].values[0]);
       $('.value3BPM').append(o.docs[2].samples[3].values[0]);
       $('.value4BPM').append(o.docs[2].samples[4].values[0]);
       $('.value5BPM').append(o.docs[2].samples[5].values[0]);
       $('.value6BPM').append(o.docs[2].samples[6].values[0]);
       $('.value7BPM').append(o.docs[2].samples[7].values[0]);
       $('.value8BPM').append(o.docs[2].samples[8].values[0]);
       $('.value9BPM').append(o.docs[2].samples[9].values[0]);
    });
}) ;
