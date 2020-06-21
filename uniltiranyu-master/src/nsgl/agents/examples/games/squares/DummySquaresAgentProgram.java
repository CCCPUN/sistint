/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package nsgl.agents.examples.games.squares;

import nsgl.agents.Action;
import nsgl.agents.AgentProgram;
import nsgl.agents.Percept;
import nsgl.generic.array.Vector;

/**
 *
 * @author Jonatan
 */
public class DummySquaresAgentProgram implements AgentProgram {
    protected String color;
    public DummySquaresAgentProgram( String color ){
        this.color = color;        
    }
    
    @Override
    public Action compute(Percept p) {
        long time = (long)(200 * Math.random());
        try{
           Thread.sleep(time);
        }catch(Exception e){}
        if( p.getAttribute(Squares.TURN).equals(color) ){
        	System.out.println(color);
            int size = Integer.parseInt((String)p.getAttribute(Squares.SIZE));
            int i = 0;
            int j = 0;
            Vector<String> v = new Vector<String>();
            while(v.size()==0){
              System.out.println("Enter");
              i = (int)(size*Math.random());
              j = (int)(size*Math.random());
              if( i == 0 || j == 0 ) System.out.println("OKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK");
              if(((String)p.getAttribute(i+":"+j+":"+Squares.LEFT)).equals(Squares.FALSE))
                v.add(Squares.LEFT);
              if(((String)p.getAttribute(i+":"+j+":"+Squares.TOP)).equals(Squares.FALSE))
                v.add(Squares.TOP);
              if(((String)p.getAttribute(i+":"+j+":"+Squares.BOTTOM)).equals(Squares.FALSE))
                v.add(Squares.BOTTOM);
              if(((String)p.getAttribute(i+":"+j+":"+Squares.RIGHT)).equals(Squares.FALSE))
                v.add(Squares.RIGHT);
            }
            System.out.println("Exit");
            try{
            	System.out.println(v.size());
            	String move = v.get((int)(Math.random()*v.size()));
                return new Action( i+":"+j+":"+move);
            }catch(Exception e){}
        }
        return new Action(Squares.PASS);
    }

    @Override
    public void init() {
    }
    
}

