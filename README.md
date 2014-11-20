Image-to-network
================

Read images and create networks out of them. Image source - pubmed

Proposed steps :-
- [x] read a .jpg file into the code and detect the text area.
- [x] Isolate the text area and process the text into tesseract. 
  - [ ] train tesseract for current data.
  - [ ] test tesseract with the data.
  - [ ] seek help from semantic concept of data. 
- [x]  Process the nodes and store them in a graph.
- [ ] detect arrowheads - arrows(->) & inhibitors(-|) .
        proposed methods - image moments, contours, SURF algorithm
- [ ] introduce links in graphs by detecting direction of arrows.
- [ ] create GPML files.
- [ ] process GPML files in s/w like cytoscape.
