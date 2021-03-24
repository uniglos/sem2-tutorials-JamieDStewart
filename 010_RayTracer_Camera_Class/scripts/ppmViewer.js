//This is the function that will be called from the index.html
function setup(){
    //call the loadPPMFromFile function with a callback function specified
    loadPPMFromFile("./bin/Debug/output.ppm",  ppmImageDataLoaded );
}

//Function to load a ppm file using xmlhttprequest
//calls the second parameter as a callback function when data has been loded
function loadPPMFromFile( a_filename, a_callback){
    var filehttpREQ = new XMLHttpRequest();
    filehttpREQ.onreadystatechange = function(){
        if( this.readyState === 4 ){
            if(this.status === 200 || this.status == 0 ){
                //file has been successfully loaded
                console.log('File Loaded: ' + a_filename);
                //send the text data to the shader loader
                a_callback(this.responseText);
            }
        }
    }
    filehttpREQ.open("GET", a_filename, true);
    filehttpREQ.send();
}

//function creates parses the loaded ppm data
//gets html file canvas element and configures size
//then gets canvas context pixel data and writes ppm data to buffer
function ppmImageDataLoaded( ppmImageData )
{
    //get the header from first three lines of file
    var headerData = ppmImageData.split("\n", 3);
    var headerLength = headerData[0].length + headerData[1].length + headerData[2].length;
    //get the image data and split the data in to an array at every space or line end
    var imageData = ppmImageData.substring(headerLength+3).split(/[\r\n\s]+/);
    
    //grab the canvas element from the document
    canvas = document.getElementById('PPM_Viewer');
    //set canvas size based on ppm image size
    var imageDimensions = headerData[1].split(" ");
    canvas.width = imageDimensions[0];
    canvas.height = imageDimensions[1];
    //give it a border
    canvas.style = "border:1px solid #000000;";
    //get the canvas context and image data buffer
    var ctx = canvas.getContext('2d');
    //clear the canvas
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    //get a reference to the canvas pixel data
    var id = ctx.getImageData(0, 0, canvas.width, canvas.height);
    var pixels = id.data;
    //iterate through the image data and copy data to canvas context
    var index = 0;
    for( var i = 0; i < imageData.length; i+=3){
        pixels[index] = imageData[i];       //Red channel
        pixels[index+1] = imageData[i+1];   //blue channel
        pixels[index+2] = imageData[i+2];   //green channel
        pixels[index+3] = 255;              //dont forget canvas has alpha channel
        index+=4;
    }
    //set image data back into canvas
    ctx.putImageData(id, 0, 0);
}