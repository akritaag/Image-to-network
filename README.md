Image-to-network
================

Read images and create networks out of them. Image source - pubmed

Proposed steps :-
- [ ] read a .jpg file into the code and detect the text area.
- [ ] Isolate the text area and process the text into tesseract. 
  - [x] train tesseract for current data.
  - [x] test tesseract with the data.
  - [x] seek help from semantic concept of data. 
- [ ]  Process the nodes and store them in a graph.
- [x] detect arrowheads - arrows(->) & inhibitors(-|) .
- [x] introduce links in graphs by detecting direction of arrows.
- [x] create GPML files.
- [x] process GPML files in s/w like cytoscape.
