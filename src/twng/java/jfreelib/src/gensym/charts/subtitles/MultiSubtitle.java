package gensym.charts.subtitles;

import java.awt.Font;
import java.awt.Paint;

import org.jfree.chart.block.BlockContainer;
import org.jfree.chart.block.EmptyBlock;
import org.jfree.chart.block.GridArrangement;
import org.jfree.chart.event.TitleChangeEvent;
import org.jfree.chart.title.CompositeTitle;
import org.jfree.chart.title.TextTitle;
import org.jfree.ui.HorizontalAlignment;
import org.jfree.ui.RectangleEdge;

/**
 * Multiple subtitle class
 */
public class MultiSubtitle extends CompositeTitle implements ISubtitle {
    /**
     * Generated version UID
     */
    private static final long serialVersionUID = -6067233397719515536L;

    /**
     * Titles separator
     */
    private final static EmptyBlock emptyBlock = new EmptyBlock(2000.0, 0.0);
    
    /**
     * Titles (left, center, right) 
     */
    private TextTitle[] titles = new TextTitle[] {new TextTitle(""), new TextTitle(""), new TextTitle("")};
    
    /**
     * Titles font
     */
    private Font font = TextTitle.DEFAULT_FONT;
    
    /**
     * Constructor
     * @param text title text
     * @param position title position
     */
    public MultiSubtitle(String text, RectangleEdge position) {
        super(new BlockContainer(new GridArrangement(1, 5)));
        
        BlockContainer block = getContainer();
        block.add(titles[0]); titles[0].setHorizontalAlignment(HorizontalAlignment.LEFT);
        block.add(emptyBlock);
        block.add(titles[1]); titles[1].setHorizontalAlignment(HorizontalAlignment.CENTER);
        block.add(emptyBlock);
        block.add(titles[2]); titles[2].setHorizontalAlignment(HorizontalAlignment.RIGHT);
        
        setSubtitleText(text);
        setFont(font);
        setPosition(position);
    }
    
    /**
     * {@inheritDoc}
     */
    public Font getFont() {
        return font;
    }

    /**
     * {@inheritDoc}
     */
    public final void setFont(Font font) {
        this.font = font;
        
        for (TextTitle title : titles) {
            title.setFont(font);
        }
        notifyListeners(new TitleChangeEvent(this));
    }

    /**
     * {@inheritDoc}
     */
    public final void setSubtitleText(String text) {
        String parsed = text.replace("|", " | ");
        String[] labels = parsed.split("[|]");

        // Make all titles empty
        for (int index = 0; index < titles.length; index++) {
            titles[index].setText("");
        }

        if (labels.length == 1) {
            titles[1].setText(labels[0].trim());
        } else {
            for (int index = 0; index < titles.length && index < labels.length; index++) {
                titles[index].setText(labels[index].trim());
            }
        }
        
        notifyListeners(new TitleChangeEvent(this));
    }

    /**
     * Gets subTitles text
     * @return subtitles
     */
    public TextTitle[] getSubtitleText() {
        return titles;
    }
    
    /**
     * Returns the paint used to display the title string.
     * @return the paint
     */
    public Paint getPaint() {
        return titles[0].getPaint();
    }
    
    /**
     * Sets the paint used to display the title string.
     * @param paint the new paint
     */
    public void setPaint(Paint paint) {
        if (!getPaint().equals(paint)) {
            for (TextTitle title : titles) {
                title.setPaint(paint);
            }
            notifyListeners(new TitleChangeEvent(this));
        }
    }
}
