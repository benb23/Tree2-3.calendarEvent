using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApplication1
{

     public class TreeNode {
         public int val;
         public TreeNode left;
          public TreeNode right;
          public TreeNode(int x) { val = x; }
      }

    public class Solution
    {
        long x=43259435984325849;
        int res;

        bool b = int.TryParse(x.ToString(), out res);

        public bool IsBalanced(TreeNode root)
        {
            int x = IsBalancedAux(root);
            return Math.Abs(x) == 1;

        }

        public int IsBalancedAux(TreeNode root)
        {
            return (IsBalancedAux(root.left) + 1) - (IsBalancedAux(root.right) + 1);
        }
    }
}
