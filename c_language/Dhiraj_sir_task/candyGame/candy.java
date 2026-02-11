import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.Random;

public class candy extends JPanel implements ActionListener, KeyListener {

    // game size
    final int WIDTH = 400;
    final int HEIGHT = 400;

    // basket
    int basketWidth = 80;
    int basketHeight = 15;
    int basketX = WIDTH / 2 - basketWidth / 2;
    int basketSpeed = 10;

    // candy
    int candySize = 15;
    int candyX;
    int candyY = 0;
    int candySpeed = 2;

    int score = 0;
    int life = 5;

    Timer timer;
    Random rand = new Random();

    public candy() {
        setPreferredSize(new Dimension(WIDTH, HEIGHT));
        setBackground(Color.BLACK);
        setFocusable(true);
        addKeyListener(this);

        spawnCandy();

        timer = new Timer(16, this); // ~60 FPS
        timer.start();
    }

    void spawnCandy() {
        candyX = rand.nextInt(WIDTH - candySize);
        candyY = 0;
    }

    @Override
    public void paintComponent(Graphics g) {
        super.paintComponent(g);

        // candy
        g.setColor(Color.RED);
        g.fillOval(candyX, candyY, candySize, candySize);

        // basket
        g.setColor(Color.YELLOW);
        g.fillRect(basketX, HEIGHT - basketHeight - 5, basketWidth, basketHeight);

        // score & life
        g.setColor(Color.WHITE);
        g.drawString("Score: " + score, 10, 15);
        g.drawString("Life: " + life, 330, 15);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        candyY += candySpeed;

        int basketY = HEIGHT - basketHeight - 5;

        // catch candy
        if (candyY + candySize >= basketY &&
            candyX + candySize >= basketX &&
            candyX <= basketX + basketWidth) {

            score++;
            candySpeed++;   // increase difficulty
            spawnCandy();
        }

        // miss candy
        if (candyY > HEIGHT) {
            life--;
            spawnCandy();
        }

        if (life <= 0) {
            timer.stop();
            JOptionPane.showMessageDialog(this,
                    "GAME OVER\nFinal Score: " + score);
            System.exit(0);
        }

        repaint();
    }

    @Override
    public void keyPressed(KeyEvent e) {
        if (e.getKeyCode() == KeyEvent.VK_LEFT && basketX > 0)
            basketX -= basketSpeed;

        if (e.getKeyCode() == KeyEvent.VK_RIGHT &&
            basketX < WIDTH - basketWidth)
            basketX += basketSpeed;
    }

    @Override public void keyReleased(KeyEvent e) {}
    @Override public void keyTyped(KeyEvent e) {}

    public static void main(String[] args) {
        JFrame frame = new JFrame("Candy Catch Game");
        candy game = new candy();

        frame.add(game);
        frame.pack();
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setResizable(false);
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);
    }
}
