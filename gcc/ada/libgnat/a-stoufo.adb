------------------------------------------------------------------------------
--                                                                          --
--                         GNAT RUN-TIME COMPONENTS                         --
--                                                                          --
--                    ADA.STRINGS.TEXT_OUTPUT.FORMATTING                    --
--                                                                          --
--                                 B o d y                                  --
--                                                                          --
--            Copyright (C) 2020, Free Software Foundation, Inc.            --
--                                                                          --
-- GNAT is free software;  you can  redistribute it  and/or modify it under --
-- terms of the  GNU General Public License as published  by the Free Soft- --
-- ware  Foundation;  either version 3,  or (at your option) any later ver- --
-- sion.  GNAT is distributed in the hope that it will be useful, but WITH- --
-- OUT ANY WARRANTY;  without even the  implied warranty of MERCHANTABILITY --
-- or FITNESS FOR A PARTICULAR PURPOSE.                                     --
--                                                                          --
-- As a special exception under Section 7 of GPL version 3, you are granted --
-- additional permissions described in the GCC Runtime Library Exception,   --
-- version 3.1, as published by the Free Software Foundation.               --
--                                                                          --
-- You should have received a copy of the GNU General Public License and    --
-- a copy of the GCC Runtime Library Exception along with this program;     --
-- see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see    --
-- <http://www.gnu.org/licenses/>.                                          --
--                                                                          --
-- GNAT was originally developed  by the GNAT team at  New York University. --
-- Extensive contributions were provided by Ada Core Technologies Inc.      --
--                                                                          --
------------------------------------------------------------------------------

pragma Ada_2020;

with Ada.Strings.Text_Output.Files;
with Ada.Strings.Text_Output.Buffers; use Ada.Strings.Text_Output.Buffers;
with Ada.Strings.Text_Output.Utils; use Ada.Strings.Text_Output.Utils;
package body Ada.Strings.Text_Output.Formatting is

   procedure Put
     (S : in out Sink'Class; T : Template;
      X1, X2, X3, X4, X5, X6 : UTF_8 := "")
   is
      J : Positive := T'First;
      Used : array (1 .. 6) of Boolean := (others => False);
   begin
      while J <= T'Last loop
         if T (J) = '\' then
            J := J + 1;
            case T (J) is
               when 'n' =>
                  New_Line (S);
               when '\' =>
                  Put_7bit (S, '\');
               when 'i' =>
                  Indent (S);
               when 'o' =>
                  Outdent (S);
               when 'I' =>
                  Indent (S, 1);
               when 'O' =>
                  Outdent (S, 1);

               when '1' =>
                  Used (1) := True;
                  Put_UTF_8 (S, X1);
               when '2' =>
                  Used (2) := True;
                  Put_UTF_8 (S, X2);
               when '3' =>
                  Used (3) := True;
                  Put_UTF_8 (S, X3);
               when '4' =>
                  Used (4) := True;
                  Put_UTF_8 (S, X4);
               when '5' =>
                  Used (5) := True;
                  Put_UTF_8 (S, X5);
               when '6' =>
                  Used (6) := True;
                  Put_UTF_8 (S, X6);

               when others =>
                  raise Program_Error;
            end case;
         else
            Put_7bit (S, T (J));
         end if;

         J := J + 1;
      end loop;

      if not Used (1) then
         pragma Assert (X1 = "");
      end if;
      if not Used (2) then
         pragma Assert (X2 = "");
      end if;
      if not Used (3) then
         pragma Assert (X3 = "");
      end if;
      if not Used (4) then
         pragma Assert (X4 = "");
      end if;
      if not Used (5) then
         pragma Assert (X5 = "");
      end if;
      if not Used (6) then
         pragma Assert (X6 = "");
      end if;

      Flush (S);
   end Put;

   procedure Put
     (T : Template;
      X1, X2, X3, X4, X5, X6 : UTF_8 := "") is
   begin
      Put (Files.Standard_Output.all, T, X1, X2, X3, X4, X5, X6);
   end Put;

   procedure Err
     (T : Template;
      X1, X2, X3, X4, X5, X6 : UTF_8 := "") is
   begin
      Put (Files.Standard_Error.all, T, X1, X2, X3, X4, X5, X6);
   end Err;

   function Format
     (T : Template;
      X1, X2, X3, X4, X5, X6 : UTF_8 := "")
     return UTF_8_Lines
   is
      Buf : Buffer := New_Buffer;
   begin
      Put (Buf, T, X1, X2, X3, X4, X5, X6);
      return Get_UTF_8 (Buf);
   end Format;

end Ada.Strings.Text_Output.Formatting;
